let handleClick = (_event, _self) => Js.log("clicked!");
let onClick = (event, _self) => Js.log(ReactDOMRe.domElementToObj(ReactEventRe.Form.target(event))##value);
let make = (~message, _children) => {
  ...ReasonReact.statelessComponent("MyPage"),
  render: (self) =>
    <div onClick=(self.handle(handleClick))>
      <input value="" onChange=(self.handle(onClick)) style=(ReactDOMRe.Style.make(~display="block", ())) />
      (ReasonReact.stringToElement(message))
    </div>
};
