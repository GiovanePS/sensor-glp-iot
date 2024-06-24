import React, { useState, useEffect } from "react";
import { Bar } from "react-chartjs-2";
import {
  Chart as ChartJS,
  CategoryScale,
  LinearScale,
  BarElement,
  Title,
  Tooltip,
  Legend,
} from "chart.js";
import "./History.css";

// Register the components for Chart.js
ChartJS.register(
  CategoryScale,
  LinearScale,
  BarElement,
  Title,
  Tooltip,
  Legend
);

const History = ({ show, onClose }) => {
  const [durations, setDurations] = useState([]);

  // Fetch data
  useEffect(() => {
    const fetchData = async () => {
      try {
        const response = await fetch("/data");
        const data = await response.json();
        setDurations(data);
      } catch (e) {
        console.error("Error fetching data:", e);
      }
    };
    fetchData();
  }, []);

  if (!show) {
    return null;
  }

  const processData = (durations) => {
    if (durations.length === 0) return { bins: [], labels: [] };

    const maxDuration = Math.max(...durations);
    const binSize = 1; // 1 second intervals
    const numBins = Math.ceil(maxDuration / binSize);
    const bins = Array(numBins).fill(0);

    durations.forEach((duration) => {
      const index = Math.floor(duration / binSize);
      bins[index] += 1;
    });

    const labels = bins.map((_, i) => {
      if (i === bins.length - 1) {
        return `${i * binSize}s+`;
      }
      return `${i * binSize}-${(i + 1) * binSize}s`;
    });

    return { bins, labels };
  };

  const { bins, labels } = processData(durations);

  const data = {
    labels: labels,
    datasets: [
      {
        label: "Activation Duration Frequency",
        data: bins,
        backgroundColor: "rgba(75,192,192,0.2)",
        borderColor: "rgba(75,192,192,1)",
        borderWidth: 1,
      },
    ],
  };

  const options = {
    responsive: true,
    plugins: {
      legend: {
        position: "top",
      },
      title: {
        display: true,
        text: "Activation Duration Frequency",
      },
    },
    scales: {
      y: {
        beginAtZero: true,
      },
    },
  };

  return (
    <div className="modal-backdrop">
      <div className="modal-content">
        <h2>History</h2>
        <div className="modal-chart">
          <Bar data={data} options={options} />
        </div>
        <button className="btn-modal" onClick={onClose}>
          Close
        </button>
      </div>
    </div>
  );
};

export default History;
