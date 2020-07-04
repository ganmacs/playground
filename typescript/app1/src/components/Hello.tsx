import * as React from "react";

interface HelloProps {
  compiler: string;
  framework: string;
}

interface HelloState {
  val: string;
  n: number;
}

export class Hello extends React.Component<HelloProps, HelloState> {
  constructor(props: HelloProps) {
    super(props);
    this.state = {
      val: props.compiler,
      n: 0,
    };
  }

  render() {
    return (
      <div>
        <button
          className="square"
          onClick={() => this.setState({ n: this.state.n + 1 })}
        >
          {this.state.val}a
        </button>
        <div>{this.state.n.toString()}</div>
      </div>
    );
  }
}
