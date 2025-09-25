<?php

namespace App\Http\Controllers;

use Illuminate\Http\Request;
use App\Services\WeatherService;

class WeatherController extends Controller
{
    protected $weatherService;

    public function __construct(WeatherService $weatherService)
    {
        $this->weatherService = $weatherService;
    }

    public function showDashboard()
    {
        // Diepenbeek
        $lat = 50.91;
        $lon = 5.41;

        // Get weather data
        $weatherData = $this->weatherService->getWeatherData($lat, $lon);

        return view('dashboard', compact('weatherData'));
    }
}
