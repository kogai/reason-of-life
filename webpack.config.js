const path = require('path');

module.exports = {
  entry: './src/index.bs.js',
  output: {
    path: path.join(__dirname, "build"),
    filename: 'bundle.js',
  },
  devServer: {
    contentBase: path.join(__dirname, "build"),
  }
};
