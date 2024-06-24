import { useState, useEffect } from "react";
import History from "./History";
import "./App.css";

const App = () => {
  const [msg, setMsg] = useState("");
  const [showChart, setShowChart] = useState(false);

  useEffect(() => {
    const ws = new WebSocket("ws://localhost:3000/ws");

    ws.onopen = () => {
      console.log("Connected to server");
    };

    ws.onmessage = (event) => {
      console.log("Event", event);
      console.log(`Msg from server: ${event.data}`);
      setMsg(event.data);
    };

    ws.onclose = () => {
      console.log("Disconnected from server");
    };

    return () => {
      ws.close();
    };
  }, []);

  const isGLP_OK = msg === "1";

  const bgColor = isGLP_OK ? "green" : "red";
  const header = isGLP_OK ? "SAFE" : "WARNING";
  const subHeader = isGLP_OK ? "No Gas Detected" : "Gas Detected";

  return (
    <div className={`container ${bgColor}`}>
      <button className="btn-history" onClick={() => setShowChart(true)}>History</button>
      <h1>{header}</h1>
      <h3>{subHeader}</h3>
      <History show={showChart} onClose={() => setShowChart(false)} />
    </div>
  );
};

export default App;
