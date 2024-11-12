<?php

namespace App\Http\Controllers;

use Illuminate\Http\Request;
use App\Models\SensorData;

class SensorDataController extends Controller
{
    // Metode untuk mendapatkan data sensor
    public function getSensorData()
    {
        // Mengambil semua data dari model SensorData
        $data = SensorData::all();

        // Mengembalikan data dalam format JSON
        return response()->json($data);
    }

    // Metode untuk menyimpan data sensor
    public function store(Request $request)
    {
        // Validasi data yang diterima
        $validated = $request->validate([
            'temperature' => 'required|numeric',
            'humidity' => 'required|numeric',
            'ph' => 'required|numeric',
            'turbidity' => 'required|numeric',
        ]);

        // Menyimpan data yang divalidasi ke dalam database
        $sensorData = SensorData::create($validated);

        // Mengembalikan response dengan status sukses
        return response()->json(['message' => 'Data saved successfully!', 'data' => $sensorData]);
    }
}

