<?php

use App\Http\Controllers\SensorDataController;

Route::get('/sensor-data', [SensorDataController::class, 'getSensorData']);
Route::post('/sensor-data', [SensorDataController::class, 'store']);
