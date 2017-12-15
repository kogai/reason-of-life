const ExtractTextPlugin = require("extract-text-webpack-plugin");
const path = require('path');

module.exports = {
  entry: './src/index.bs.js',
  output: {
    path: path.join(__dirname, "build"),
    filename: 'bundle.js',
  },
  devServer: {
    contentBase: path.join(__dirname, "build"),
  },
  module: {
    rules: [{
      test: /\.css$/,
      use: ExtractTextPlugin.extract({
        fallback: "style-loader",
        use: [{
          loader: "css-loader",
          query: {
            modules: true,
            sourceMap: true,
            importLoaders: 2,
            localIdentName: "[name]__[local]___[hash:10]",
          }
        }, "postcss-loader"],
      }),
    }]
  },
  plugins: [
    new ExtractTextPlugin("style.css"),
  ]
};
