const ws = new WebSocket("ws://localhost:3000/");

ws.onopen = () => {
    console.log("Connected to server");
}

ws.onmessage = ({data}) => {
    console.log(`Msg from server: ${data}`);

    const msgDiv = document.getElementById("msgDiv");
    const msg = document.createElement("p");
    msg.innerText = data;
    msgDiv.appendChild(msg);
}

ws.onclose = () => {
    console.log("Disconnected from server");
}

document.querySelector("button").onclick = () => {
    ws.send("Hello from client!")
}

document.getElementById("btn").onclick = () => {
    const input = document.getElementById("msgInput");
    ws.send(input.value);
    input.value = "";
}