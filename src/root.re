type state = {
  value: string,
  size: int,
  board: list(list(Cell.t))
};

type action =
  | Inc
  | Dec
  | Click
  | Change(string);

let handleClick = (_event, _self) => Js.log("clicked!");

let onChange = (event) => {
  let value = ReactDOMRe.domElementToObj(ReactEventRe.Form.target(event))##value;
  Change(value)
};

let onClick = (_) => Click;

let inc = (_) => Inc;

let dec = (_) => Dec;

let rec range = (n) =>
  switch n {
  | 0 => []
  | n => [n, ...range(n - 1)]
  };

let make = (_children) => {
  ...ReasonReact.reducerComponent("Page"),
  initialState: () => {
    value: "",
    size: 16,
    board: 16
      |> range
      |> List.rev
      |> List.map (y =>
        16
        |> range
        |> List.rev
        |> List.map (x => {
          Cell.x: x,
          y: y,
          status: Cell.Death 
        }))
  },
  reducer: (a, s) =>
    switch a {
    | Change(value) => ReasonReact.Update({...s, value})
    | Click => ReasonReact.Update({...s, size: s.size + 1})
    | Inc => ReasonReact.Update({...s, size: s.size + 1})
    | Dec => ReasonReact.Update({...s, size: s.size - 1})
    },
  render: (self) =>
    <div onClick=(self.handle(handleClick))>
      <div className="buttons has-addons myActive">
        <button className="button" onClick=(self.reduce(inc))>
          (ReasonReact.stringToElement("Plus"))
        </button>
        <button className="button" onClick=(self.reduce(dec))>
          (ReasonReact.stringToElement("Minus"))
        </button>
      </div>
      (
        self.state.board
        |> List.mapi(idx => xs =>
          xs
          |> List.map(({ Cell.x, y, status }) =>
            <Cell
              key=(string_of_int(x) ++ string_of_int(y))
              status=(status)
              x=(x)
              y=(y)
              />)
          |> Array.of_list
          |> ReasonReact.arrayToElement
          |> (c => <div
            className=(RootCss.style##my)
            key=(string_of_int(idx))
          >(c)</div>)
        )
        |> Array.of_list
        |> ReasonReact.arrayToElement
      )
    </div>
};
