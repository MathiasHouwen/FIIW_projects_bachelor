<?php

use Illuminate\Support\Facades\Route;

Route::get('/', function () {
    return view('welcome');
});

Auth::routes();

Route::get('/home', [App\Http\Controllers\HomeController::class, 'index'])->name('home');
Route::post('/register-user', [App\Http\Controllers\UserController::class, 'registerUser']);
Route::post('/login-user', [App\Http\Controllers\UserController::class, 'loginUser']);
