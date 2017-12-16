[@bs.module] external cx : (string, string) => string = "classnames";

type life =
  | Live
  | Death;

type t = {status: life};

let make = (~status, _children) => {
  ...ReasonReact.statelessComponent("Cell"),
  render: (_self) => {
    Js.log(CellCss.style);
    <div
      className=(cx(
        switch status {
        | Live => CellCss.style##myActive
        | Death => CellCss.style##myInActive
        }, CellCss.style##my
      ))
    />
  }
};
