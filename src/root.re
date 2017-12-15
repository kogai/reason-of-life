/* [@bs.module] external style : Js.t({..}) = "./root.css"; */

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
    <div onClick=(self.handle(handleClick))>
      <div className="buttons has-addons myActive">
        <button className="button" onClick=(self.reduce(inc))>
          (ReasonReact.stringToElement("Plus"))
        </button>
        <button className="button" onClick=(self.reduce(dec))>
          (ReasonReact.stringToElement("Minus"))
        </button>
      </div>
      /* (ReasonReact.arrayToElement([| */
        <Cell status=(Cell.Live) />
        <Cell status=(Cell.Death) />
        /* |])) */
    </div>
  }
};
