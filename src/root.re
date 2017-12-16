type state = {
  period: int,
  size: int,
  board: list(list(Cell.t))
};

type action =
  | Inc
  | Dec
  | Spawn(int, int)
  | Play(int)
  | Tick;

let inc = (_) => Inc;

let dec = (_) => Dec;

let spawn = (x, y, _) => Spawn(x, y);

let play = (n, _) => Play(n);

let next = (board) => {
  let survive = (x, y, status) => {
    let arround = [
      ((-1), (-1)),
      (0, (-1)),
      (1, (-1)),
      ((-1), 0),
      (1, 0),
      ((-1), 1),
      (0, 1),
      (1, 1)
    ];
    let survivers =
      arround
      |> List.map(
           ((mx, my)) =>
             try (
               y
               + my
               |> List.nth(board)
               |> ((xs) => List.nth(xs, x + mx))
               |> (({Cell.status}) => status == Cell.Live)
             ) {
             | Failure(_) => false
             }
         )
      |> List.filter((t) => t);
    Cell.(
      switch status {
      | Death => List.length(survivers) == 3
      | Live =>
        let n = List.length(survivers);
        n == 2 || n == 3
      }
    )
  };
  board
  |> List.map(
       List.map(
         ({Cell.x, y, status}) => {
           Cell.x,
           y,
           status: survive(x, y, status) ? Cell.Live : Cell.Death
         }
       )
     )
};

[@bs.val] external setTimeout : (unit => unit, int) => float = "setTimeout";

let tick = (reduce, p, b) => {
  let rec tickImpl = (period, board) =>
    switch period {
    | 0 => ()
    | _ =>
      ignore(
        setTimeout(
          () => {
            Js.log("called.");
            reduce(() => Tick, ());
            tickImpl(period - 1, next(board))
          },
          100
        )
      )
    };
  tickImpl(p, b)
};

/* ignore(
     setTimeout(
       () => {
         Js.log("called.");
         reduce(() => Tick, ())
       },
       100
     )
   ) */
exception Unreachable;

let make = (_children) => {
  ...ReasonReact.reducerComponent("Page"),
  initialState: () => {
    period: 10,
    size: 16,
    board:
      Utils.(
        16
        |> range
        |> List.rev
        |> List.map(
             (y) => 16 |> range |> List.rev |> List.map((x) => {Cell.x, y, status: Cell.Death})
           )
      )
  },
  reducer: (a, s) =>
    switch a {
    | Inc => ReasonReact.Update({...s, size: s.size + 1})
    | Dec => ReasonReact.Update({...s, size: s.size - 1})
    | Tick => ReasonReact.Update({...s, board: next(s.board)})
    | Play(n) => ReasonReact.SideEffects((({reduce}) => tick(reduce, n, s.board)))
    | Spawn(mx, my) =>
      ReasonReact.Update({
        ...s,
        board:
          s.board
          |> List.map(
               List.map(
                 ({Cell.x, y} as cell) => x == mx && y == my ? {...cell, status: Cell.Live} : cell
               )
             )
      })
    },
  render: (self) =>
    <div>
      <div className="buttons has-addons myActive">
        <button className="button" onClick=(self.reduce(inc))>
          (ReasonReact.stringToElement("Plus"))
        </button>
        <button className="button" onClick=(self.reduce(dec))>
          (ReasonReact.stringToElement("Minus"))
        </button>
        <button className="button" onClick=(self.reduce(play(self.state.period)))>
          (
            ReasonReact.stringToElement(
              Printf.sprintf("Play(%s)", string_of_int(self.state.period))
            )
          )
        </button>
      </div>
      (
        self.state.board
        |> List.mapi(
             (idx, xs) =>
               xs
               |> List.map(
                    ({Cell.x, y, status}) =>
                      <Cell
                        key=(string_of_int(x) ++ "," ++ string_of_int(y))
                        status
                        onClick=(self.reduce(spawn(x, y)))
                      />
                  )
               |> Array.of_list
               |> ReasonReact.arrayToElement
               |> ((c) => <div className=RootCss.style##my key=(string_of_int(idx))> c </div>)
           )
        |> Array.of_list
        |> ReasonReact.arrayToElement
      )
    </div>
};