import { useState, useEffect } from "react";
import "./App.css";

const App = () => {
  const [msg, setMsg] = useState("");

  useEffect(() => {
    const ws = new WebSocket("ws://localhost:3000");

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

  const bgColor = msg === "1" ? "green" : "red";
  const message = msg === "1" ? "GLP Detector is OFF" : "VAGABUNDO DETECTADO";

  return (
    <div className={`container ${bgColor}`}>
      <button className="button">Historico</button>
      <h1>{message}</h1>
    </div>
  );
};

export default App;
