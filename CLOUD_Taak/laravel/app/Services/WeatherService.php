<?php

namespace App\Services;

use Illuminate\Support\Facades\Http;
use Illuminate\Support\Facades\Log;

class WeatherService
{
    public function getWeatherData($lat, $lon)
    {
        $apiKey = env('OPENWEATHER_API_KEY');

        if (!$apiKey) {
            Log::error('Missing OpenWeather API Key in .env file');
            return null;
        }

        $url = "https://api.openweathermap.org/data/2.5/weather?lat={$lat}&lon={$lon}&appid={$apiKey}";

        $response = Http::get($url);

        if ($response->successful()) {
            Log::info('Weather API Response:', $response->json()); // Debugging
            return $response->json();
        }

        Log::error('Weather API request failed:', [
            'status' => $response->status(),
            'body' => $response->body(),
        ]);

        return null;
    }
}
