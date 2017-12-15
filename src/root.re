type state = {
  value: string,
  size: int
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
  initialState: () => {value: "", size: 8},
  reducer: (a, s) =>
    switch a {
    | Change(value) => ReasonReact.Update({...s, value})
    | Click => ReasonReact.Update({...s, size: s.size + 1})
    | Inc => ReasonReact.Update({...s, size: s.size + 1})
    | Dec => ReasonReact.Update({...s, size: s.size - 1})
    },
  render: (self) => {
    let xs =
      self.state.size
      |> range
      |> List.map((n) => ReasonReact.stringToElement(string_of_int(n)))
      |> Array.of_list;
    <div onClick=(self.handle(handleClick))>
      <div className="buttons has-addons">
        <button className="button" onClick=(self.reduce(inc))>
          (ReasonReact.stringToElement("Plus"))
        </button>
        <button className="button" onClick=(self.reduce(dec))>
          (ReasonReact.stringToElement("Minus"))
        </button>
      </div>
      (ReasonReact.arrayToElement(xs))
    </div>
  }
};
