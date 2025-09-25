<?php

namespace App\Http\Controllers;

use Illuminate\Http\Request;
use Illuminate\Support\Facades\Http;

class GraphQLController extends Controller
{
    /**
     * Show the form for entering the user ID.
     */
    public function showForm()
    {
        return view('graphql-form');
    }

    /**
     * Fetch user data from the GraphQL endpoint.
     */
    public function fetchData(Request $request)
    {
        // Validate the input
        $request->validate([
            'user_id' => 'required|integer',
        ]);

        $userId =  (int) $request->input('user_id');

        // GraphQL endpoint URL
        $graphqlEndpoint = env('GRAPHQL_ENDPOINT');

        // GraphQL query with Int type for user id
        $query = '
        query($id: Int!) {
            user(id: $id) {
                id
                name
                email
            }
        }
        ';

        $variables = [
        'id' => $userId,
        ];

        $response = Http::post($graphqlEndpoint, [
        'query' => $query,
        'variables' => $variables,
        ]);

        // Check if the request was successful
        if ($response->successful()) {
            $data = $response->json();
            return view('graphql-form', [
                'userData' => $data['data']['user'] ?? null,
                'errors' => $data['errors'] ?? null,
            ]);
        } else {
            return view('graphql-form', [
                'errorMessage' => 'Failed to fetch data from the GraphQL endpoint.',
            ]);
        }
    }

}
