type life =
  | Live
  | Death;

type t = {
  status: life
};

let make = (~status, _children) => {
  ...ReasonReact.statelessComponent("Cell"),
  render: (_self) => {
    <div className=(switch status {
      | Live => "active"
      | Death => "disable"
    })>(ReasonReact.stringToElement("OK"))</div>
  }
};
