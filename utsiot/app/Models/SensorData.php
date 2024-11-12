<?php

namespace App\Models;

use Illuminate\Database\Eloquent\Factories\HasFactory;
use Illuminate\Database\Eloquent\Model;

class SensorData extends Model
{
    use HasFactory;

    // Menentukan kolom yang dapat diisi melalui mass assignment
    protected $fillable = ['temperature', 'humidity', 'ph', 'turbidity'];

    // Jika tabel menggunakan nama selain default (misalnya, 'sensor_data')
    protected $table = 'sensor_data';
}
