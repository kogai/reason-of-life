type state = {value: string};

type action =
  | Change(string);

let handleClick = (_event, _self) => Js.log("clicked!");

let onChange = (event) => {
  let value = (ReactDOMRe.domElementToObj(ReactEventRe.Form.target(event))##value);
  Change(value)
};

let make = (~message, _children) => {
  ...ReasonReact.reducerComponent("Page"),
  /* ...ReasonReact.statelessComponent("MyPage"), */
  initialState: () => {value: ""},
  reducer: (a, _s) =>
     switch a {
       | Change(value) => ReasonReact.Update({ value: value })
    },
  render: (self) =>
    <div onClick=(self.handle(handleClick))>
      (ReasonReact.stringToElement(string_of_int(100)))
      <input
        value=(self.state.value)
        onChange=(self.reduce(onChange))
        style=(ReactDOMRe.Style.make(~display="block", ()))
      />
      (ReasonReact.stringToElement(message))
      (ReasonReact.stringToElement(self.state.value))
    </div>
};
