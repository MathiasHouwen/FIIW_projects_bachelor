<?php

use Illuminate\Support\Facades\Route;

Route::get('/', function () {
    return view('welcome');
});

Auth::routes();

Route::get('/home', [App\Http\Controllers\HomeController::class, 'index'])->name('home');
Route::post('/register-user', [App\Http\Controllers\UserController::class, 'registerUser']);
Route::post('/login-user', [App\Http\Controllers\UserController::class, 'loginUser']);

Route::get('/graphql', [App\Http\Controllers\GraphQLController::class, 'showForm'])->name('graphql.form');
Route::post('/graphql', [App\Http\Controllers\GraphQLController::class, 'fetchData'])->name('graphql.fetch');

Route::get('/dashboard', function () {return view('dashboard');})->name('dashboard');

Route::get('/km-teller', [App\Http\Controllers\KmTellerController::class, 'index']);
Route::get('/km-teller/get-total', [App\Http\Controllers\KmTellerController::class, 'getTotalKilometers'])->name('kmTeller.getTotal');
Route::post('/km-teller/add', [App\Http\Controllers\KmTellerController::class, 'addKilometers'])->name('kmTeller.add');
