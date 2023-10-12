using Distances

function get_distance_method()
    while true
        print("Choose a distance method (Euclidean or Manhattan): ")
        method = lowercase(readline())

        if method == "euclidean"
            return Euclidean()
        elseif method == "manhattan"
            return Cityblock()
        else
            println("Invalid input. Please enter 'Euclidean' or 'Manhattan'.")
        end
    end
end

function get_point_coordinates(point_name::String)::Vector{Float64}
    while true
        print("Enter coordinates for the ", point_name, " point (x y z): ")
        input = readline()
        coords = split(input)

        if length(coords) != 3
            println("You must enter exactly 3 coordinates for each point.")
            continue
        end

        try
            return parse.(Float64, coords)
        catch e
            println("Error: ", e)
        end
    end
end

function calculate_and_print_distance()
    p1 = get_point_coordinates("first")
    p2 = get_point_coordinates("second")

    distance_method = get_distance_method()
    distance = evaluate(distance_method, p1, p2)

    println("Distance using ", distance_method == Euclidean() ? "Euclidean" : "Manhattan", " method: ", round(distance))
end

calculate_and_print_distance()