import React, { useState } from "react";
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

const tempHumData = [
  { temperature: 22, humidity: 45 },
  { temperature: 18, humidity: 50 },
  { temperature: 25, humidity: 55 },
  { temperature: 20, humidity: 40 },
  { temperature: 24, humidity: 60 },
];

const timeLabels = ["5 AM", "6 AM", "7 AM", "8 AM", "9 AM"];

const History = ({ show, onClose }) => {

    const [durations, setDurations] = useState([]);

  if (!show) {
    return null;
  }

  return (
    <div className="modal-back">
      <div className="modal-content">
        <h2>History</h2>
        <div className="modal-chart">
          <Bar
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
          />
        </div>
        <button className="btn-modal" onClick={onClose}>
          Close
        </button>
      </div>
    </div>
  );
};

export default History;
