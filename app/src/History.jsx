import React, { useState, useEffect } from "react";
import "./History.css";
import { Bar, Line } from "react-chartjs-2";
import {
  Chart as ChartJS,
  CategoryScale,
  LinearScale,
  PointElement,
  LineElement,
  Title,
  Tooltip,
  Legend,
} from "chart.js";

ChartJS.register(
  CategoryScale,
  LinearScale,
  PointElement,
  LineElement,
  Title,
  Tooltip,
  Legend
);

const timeLabels = ["5 AM", "6 AM", "7 AM", "8 AM", "9 AM"];

const History = ({ show, onClose }) => {
  const [durations, setDurations] = useState([]);

  // useEffect(() => {
  //   const fetchData = async () => {
  //     try {
  //       const response = await fetch("/data");
  //       if (!response.ok) {
  //         throw new Error(`HTTP error! status: ${response.status}`);
  //       }

  //       const contentType = response.headers.get("content-type");
  //       if (!contentType || !contentType.includes("application/json")) {
  //         throw new TypeError("Received response is not in JSON format");
  //       }
        
  //       const data = await response.json();
  //       setDurations(data);
  //     } catch (e) {
  //       console.error("Error fetching data:", e);
  //     }
  //   };

  //   fetchData();
  // }, []);

   useEffect(() => {
     fetch("http://localhost:3000/data")
       .then((response) => response.json())
       .then((data) => setDurations(data))
       .catch((error) => console.error("Error fetching data:", error));
   }, []);

  if (!show) {
    return null;
  }

  return (
    <div className="modal-back">
      <div className="modal-content">
        <h2>History</h2>
        <div className="modal-chart">
          {/* <Bar
            data={{
              labels: timeLabels,
              datasets: [
                {
                  label: "Temperature",
                  data: tempHumData.map((data) => data.temperature),
                },
                {
                  label: "Humidity",
                  data: tempHumData.map((data) => data.humidity),
                },
              ],
            }}
            options={{
              elements: {
                line: {
                  tension: 0.5, // Tensão das linhas para suavização
                },
              },
              plugins: {
                title: {
                  display: true,
                  text: "Temperature & Humidity Levels",
                },
              },
              scales: {
                y: {
                  beginAtZero: true,
                  title: {
                    display: true,
                    text: "Value",
                  },
                },
              },
            }}
          /> */}
          <div>
            {/* Render your durations data here */}
            {durations.map((duration, index) => (
              <p key={index}>{duration}</p>
            ))}
          </div>
        </div>
        <button className="btn-modal" onClick={onClose}>
          Close
        </button>
      </div>
    </div>
  );
};

export default History;
