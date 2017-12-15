[@bs.module] external style : Js.t({..}) = "./cell.css";
[@bs.module] external cx : (string, string) => string = "classnames";

type life =
  | Live
  | Death;

type t = {status: life};

let make = (~status, _children) => {
  ...ReasonReact.statelessComponent("Cell"),
  render: (_self) => {
    Js.log(style);
    <div
      className=(cx(
        switch status {
        | Live => style##myActive
        | Death => style##myInActive
        }, style##my
      ))
    />
  }
};
