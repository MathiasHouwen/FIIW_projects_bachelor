require 'sinatra'
require 'graphql'

# User Data (hardcoded)
USERS = [
  { id: 1, name: 'Alice', email: 'alice@example.com' },
  { id: 2, name: 'Bob', email: 'bob@example.com' }
]

# Define GraphQL Types
class UserType < GraphQL::Schema::Object
  field :id, Integer, null: false
  field :name, String, null: false
  field :email, String, null: false
end

# Define the Query Type
class QueryType < GraphQL::Schema::Object
  field :user, UserType, null: true do
    argument :id, Integer, required: true
  end

  def user(id:)
    USERS.find { |user| user[:id] == id }
  end
end

# Define the Schema
class MySchema < GraphQL::Schema
  query(QueryType)
end

# Sinatra App
post '/graphql' do
  request_payload = JSON.parse(request.body.read)
  result = MySchema.execute(
    request_payload['query'],
    variables: request_payload['variables']
  )
  content_type :json
  result.to_json
end