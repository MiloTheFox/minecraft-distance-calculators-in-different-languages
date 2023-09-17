# Function to calculate Euclidean Distance
function euclidean_distance(x1::Float64, y1::Float64, z1::Float64, x2::Float64, y2::Float64, z2::Float64)::Float64
    return round(sqrt((x2 - x1)^2 + (y2 - y1)^2 + (z2 - z1)^2))
end

# Function to calculate Manhattan Distance
function manhattan_distance(x1::Float64, y1::Float64, z1::Float64, x2::Float64, y2::Float64, z2::Float64)::Float64
    return round(abs(x2 - x1) + abs(y2 - y1) + abs(z2 - z1))
end

function choose_distance_method()
    while true
        print("Choose a distance method (Euclidean or Manhattan): ")
        method = lowercase(readline())

        if method == "euclidean"
            return euclidean_distance
        elseif method == "manhattan"
            return manhattan_distance
        else
            println("Invalid input. Please enter 'Euclidean' or 'Manhattan'.")
        end
    end
end

function get_point_coordinates(point_name::String)::Tuple{Float64, Float64, Float64}
    while true
        try
            print("Enter coordinates for the ", point_name, " point (x y z): ")
            input = readline()
            if !isa(input, AbstractString)
                throw(ArgumentError("Expected string input"))
            end
            x, y, z = input |> split |> x -> parse.(Float64, x)

            if length([x, y, z]) != 3
                throw(ArgumentError("You must enter exactly 3 coordinates for each point."))
            end

            return (x, y, z)
        catch e
            if isa(e, ArgumentError)
                println("Error: ", e)
            else
                rethrow(e)
            end
        end
    end
end



function calculate_and_print_distance()
    x1, y1, z1 = get_point_coordinates("first")
    x2, y2, z2 = get_point_coordinates("second")

    distance_method = choose_distance_method()
    distance = distance_method(x1, y1, z1, x2, y2, z2)

    println("Distance using ", distance_method == euclidean_distance ? "Euclidean" : "Manhattan", " method: ", distance)
end

calculate_and_print_distance()
