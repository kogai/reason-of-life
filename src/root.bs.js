// Generated by BUCKLESCRIPT VERSION 2.1.0, PLEASE EDIT WITH CARE
'use strict';

var List        = require("bs-platform/lib/js/list.js");
var $$Array     = require("bs-platform/lib/js/array.js");
var Block       = require("bs-platform/lib/js/block.js");
var Curry       = require("bs-platform/lib/js/curry.js");
var React       = require("react");
var Pervasives  = require("bs-platform/lib/js/pervasives.js");
var ReasonReact = require("reason-react/src/ReasonReact.js");

function handleClick(_, _$1) {
  console.log("clicked!");
  return /* () */0;
}

function onChange($$event) {
  var value = $$event.target.value;
  return /* Change */[value];
}

function onClick() {
  return /* Click */2;
}

function inc() {
  return /* Inc */0;
}

function dec() {
  return /* Dec */1;
}

function range(n) {
  if (n !== 0) {
    return /* :: */[
            n,
            range(n - 1 | 0)
          ];
  } else {
    return /* [] */0;
  }
}

function make() {
  var newrecord = ReasonReact.reducerComponent("Page").slice();
  newrecord[/* render */9] = (function (self) {
      var xs = $$Array.of_list(List.map(Pervasives.string_of_int, range(self[/* state */2][/* size */1])));
      console.log(xs);
      return React.createElement("div", {
                  onClick: Curry._1(self[/* handle */0], handleClick)
                }, React.createElement("div", {
                      className: "buttons has-addons"
                    }, React.createElement("button", {
                          className: "button",
                          onClick: Curry._1(self[/* reduce */1], inc)
                        }, "Plus"), React.createElement("button", {
                          className: "button",
                          onClick: Curry._1(self[/* reduce */1], dec)
                        }, "Minus")), xs);
    });
  newrecord[/* initialState */10] = (function () {
      return /* record */[
              /* value */"",
              /* size */8
            ];
    });
  newrecord[/* reducer */12] = (function (a, s) {
      if (typeof a === "number") {
        if (a !== 1) {
          return /* Update */Block.__(0, [/* record */[
                      /* value */s[/* value */0],
                      /* size */s[/* size */1] + 1 | 0
                    ]]);
        } else {
          return /* Update */Block.__(0, [/* record */[
                      /* value */s[/* value */0],
                      /* size */s[/* size */1] - 1 | 0
                    ]]);
        }
      } else {
        return /* Update */Block.__(0, [/* record */[
                    /* value */a[0],
                    /* size */s[/* size */1]
                  ]]);
      }
    });
  return newrecord;
}

exports.handleClick = handleClick;
exports.onChange    = onChange;
exports.onClick     = onClick;
exports.inc         = inc;
exports.dec         = dec;
exports.range       = range;
exports.make        = make;
/* react Not a pure module */
