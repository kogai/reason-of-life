type state = {
  size: int,
  board: list(list(Cell.t))
};
type action =
  | Inc
  | Dec
  | Spawn
  | Play;
let inc = (_) => Inc;
let dec = (_) => Dec;
let spawn = (_) => Spawn;
let play = (_) => Play;

let make = (_children) => {
  ...ReasonReact.reducerComponent("Page"),
  initialState: () => {
    size: 16,
    board:
    Utils.(16
      |> range
      |> List.rev
      |> List.map(
           (y) => 16 |> range |> List.rev |> List.map((x) => {Cell.x, y, status: Cell.Death})
         ))
  },
  reducer: (a, s) =>
    switch a {
    | Inc => ReasonReact.Update({...s, size: s.size + 1})
    | Dec => ReasonReact.Update({...s, size: s.size - 1})
    | Play => raise ""
    | Spaw => raise ""
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
        <button className="button" onClick=(self.reduce(spawn))>
          (ReasonReact.stringToElement("Spawn"))
        </button>
        <button className="button" onClick=(self.reduce(play))>
          (ReasonReact.stringToElement("Play"))
        </button>
      </div>
      (
        self.state.board
        |> List.mapi(
             (idx, xs) =>
               xs
               |> List.map(
                    ({Cell.x, y, status}) =>
                      <Cell key=(string_of_int(x) ++ "," ++ string_of_int(y)) status />
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
