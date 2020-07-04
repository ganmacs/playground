const path = require("path");

module.exports = {
  mode: "production",
  devtool: "source-map",
  entry: "./src/index.tsx",
  output: {
    filename: "main.js",
    path: path.resolve(__dirname, "dist"),
  },
  module: {
    rules: [
      {
        test: /\.tsx?$/,
        use: {
          loader: "ts-loader",
          options: {
            transpileOnly: true,
          },
        },
      },
      {
        enforce: "pre",
        test: /\.js$/,
        loader: "source-map-loader",
      },
    ],
  },
  resolve: {
    extensions: [".js", ".ts", ".tsx"],
  },
  externals: {
    react: "React",
    "react-dom": "ReactDOM",
  },
};
