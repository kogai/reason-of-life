[@bs.module] external cx : (string, string) => string = "classnames";

type life =
  | Live
  | Death;

type t = {
  x: int,
  y: int,
  status: life
};

let make = (~status, ~onClick, _children) => {
  ...ReasonReact.statelessComponent("Cell"),
  render: (_self) =>
    <div
      onClick
      className=(
        cx(
          switch status {
          | Live => CellCss.style##myActive
          | Death => CellCss.style##myInActive
          },
          CellCss.style##my
        )
      )
    />
};