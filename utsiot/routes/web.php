<?php

use App\Http\Controllers\SensorDataController;

Route::get('/api/sensor-data', [SensorDataController::class, 'getSensorData']);
Route::post('/api/sensor-data', [SensorDataController::class, 'store']);

use App\Http\Controllers\MqttController;

Route::get('mqtt/subscribe', [MqttController::class, 'subscribe']);



