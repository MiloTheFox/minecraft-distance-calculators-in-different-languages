class DistanceCalculator
{
    // Defining an 3D-Point-Class with X, Y and Z for the Coordinates
    public class Point3D(double x, double y, double z)
    {
        public double X { get; } = x;
        public double Y { get; } = y;
        public double Z { get; } = z;
    }
    
    // Enum for the selection of the distance method
    public enum DistanceMethod
    {
        Euclidean,
        Manhattan
    }

    static void Main()
    {
        Point3D? point1 = GetPointFromUser("Please provide the first point (x y z): ");
        Point3D? point2 = GetPointFromUser("Please provide the second point (x y z): ");
        DistanceMethod? choice = GetDistanceMethod();
        if (point1 == null || point2 == null || !choice.HasValue) return;

        // Selecting the distance method based on the user's input
        var distance = choice switch
        {
            // Calculating the euclidean distance between 2 points
            DistanceMethod.Euclidean => CalculateEuclideanDistance(in point1, in point2),
            // Calculating the manhattan distance between 2 points
            DistanceMethod.Manhattan => CalculateManhattanDistance(in point1, in point2),
            _ => throw new InvalidOperationException("This distance method is not existent yet!")
        };

        Console.WriteLine($"The {(choice == DistanceMethod.Euclidean ? "Euclidean" : "Manhattan")} distance is: {distance:F2}");
    }

    static double CalculateEuclideanDistance(in Point3D point1, in Point3D point2)
    {
        return Math.Sqrt(Math.Pow(point1.X - point2.X, 2) + Math.Pow(point1.Y - point2.Y, 2) + Math.Pow(point1.Z - point2.Z, 2));
    }

    static double CalculateManhattanDistance(in Point3D point1, in Point3D point2)
    {
        return Math.Abs(point1.X - point2.X) + Math.Abs(point1.Y - point2.Y) + Math.Abs(point1.Z - point2.Z);
    }

    static Point3D? GetPointFromUser(string prompt)
    {
        while (true)
        {
            Console.Write(prompt);
            string input = Console.ReadLine() ?? string.Empty;
            if (string.IsNullOrWhiteSpace(input))
            {
                Console.WriteLine("You have to provide at least 3 numbers!");
                Console.ReadKey();
            }
            if (ValidateInput(input, out var result))
                return result;
            Console.WriteLine($"Incorrect Input! Please provide a total of 3 numbers! {Environment.NewLine}");
        }
    }

    // Method to check if the input can be parsed into a double
    static bool ValidateInput(string input, out Point3D? result)
    {
        var parts = input.Split(" ", StringSplitOptions.RemoveEmptyEntries);
        if (parts.Length != 3 ||
        !double.TryParse(parts[0], out var x) ||
        !double.TryParse(parts[1], out var y) ||
        !double.TryParse(parts[2], out var z))
        {
            result = default;
            return false;
        }
        result = new Point3D(x, y, z);
        return true;
    }
    
    static DistanceMethod? GetDistanceMethod()
    {
        do
        {
            // Prompt the user to select the distance method
            Console.WriteLine($"Choose the method: {Environment.NewLine}1 - Euclidean Distance{Environment.NewLine}2 - Manhattan Distance");
            var input = Console.ReadLine();
            switch (input)
            {
                case "1":
                    return DistanceMethod.Euclidean;
                case "2":
                    return DistanceMethod.Manhattan;
                default:
                    Console.WriteLine($"Incorrect input! Please use \"1\" for the euclidean distance or \"2\" for the manhattan distance an!{Environment.NewLine}");
                    break;
            }
        } while (true);
    }
}
