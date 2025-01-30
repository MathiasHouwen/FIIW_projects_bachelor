<?php

namespace App\Http\Controllers;

use Illuminate\Http\Request;

class KmTellerController extends Controller
{
    private $wsdlUrl = "http://localhost:3007/kmTellerService?wsdl";

    public function index()
    {
        return view('km_teller');
    }

    public function getTotalKilometers()
    {
        try {

            $client = new \SoapClient($this->wsdlUrl);
            $response = $client->getTotalKilometers();
            
            $totalKm = $response->return;

            return redirect()->back()->with('total_km', $totalKm);
        } catch (\Exception $e) {
            return response()->json(['error' => $e->getMessage()], 500);
        }
    }

    public function addKilometers(Request $request)
    {
        $kilometers = (int) $request->input('kilometers'); // Convert input to integer

        try {
            $client = new \SoapClient($this->wsdlUrl, [
                'trace' => 1,
                'exceptions' => true
            ]);

            // Correct parameter format based on WSDL (Use 'arg0' instead of 'kilometers')
            $params = ['arg0' => $kilometers];

            // Call SOAP method
            $response = $client->__soapCall('addKilometers', [$params]);

            return response()->json([
                'message' => 'Kilometers added successfully!',
                'total_km' => $response->return ?? 0
            ]);
        } catch (\SoapFault $e) {
            return response()->json([
                'error' => 'SOAP Fault: ' . $e->getMessage()
            ], 500);
        }
    }
}
