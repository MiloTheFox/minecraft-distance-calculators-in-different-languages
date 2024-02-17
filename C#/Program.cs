struct Point3D
{
    public double X { get; }
    public double Y { get; }
    public double Z { get; }

    public Point3D(double x, double y, double z)
    {
        X = x;
        Y = y;
        Z = z;
    }
}

enum DistanceMethod
{
    Euclidean,
    Manhattan
}

class DistanceCalculator
{
    static void Main()
    {
        Point3D? point1 = GetPointFromUser("Please provide the first point (x y z): ");
        Point3D? point2 = GetPointFromUser("Please provide the second point (x y z): ");
        DistanceMethod? choice = GetDistanceMethod();
        if (point1 == null || point2 == null || !choice.HasValue) return;

        var (dx, dy, dz) = CalculateDifferences(point1.Value, point2.Value);

        double distance = choice switch
        {
            DistanceMethod.Euclidean => CalculateEuclideanDistance(dx, dy, dz),
            DistanceMethod.Manhattan => CalculateManhattanDistance(dx, dy, dz),
            _ => 0
        };

        Console.WriteLine($"The {(choice == DistanceMethod.Euclidean ? "Euclidean" : "Manhattan")} distance is: {distance:F2}");
    }

    static (double dx, double dy, double dz) CalculateDifferences(Point3D point1, Point3D point2)
    {
        return (point1.X - point2.X, point1.Y - point2.Y, point1.Z - point2.Z);
    }

    static double CalculateEuclideanDistance(double dx, double dy, double dz)
    {
        return Math.Sqrt(dx * dx + dy * dy + dz * dz);
    }

    static double CalculateManhattanDistance(double dx, double dy, double dz)
    {
        return Math.Abs(dx) + Math.Abs(dy) + Math.Abs(dz);
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
                continue;
            }
            if (ValidateInput(input, out var result))
                return result;
            Console.WriteLine($"Incorrect Input! Please provide a total of 3 numbers! {Environment.NewLine}");
        }
    }

    static bool ValidateInput(string input, out Point3D? result)
    {
        var parts = input.Split(" ", StringSplitOptions.RemoveEmptyEntries);
        double[] coordinates = new double[3];
        if (parts.Length != 3)
        {
            result = default;
            return false;
        }
        for (int i = 0; i < 3; i++)
        {
            if (!double.TryParse(parts[i], out coordinates[i]))
            {
                result = default;
                return false;
            }
        }
        result = new Point3D(coordinates[0], coordinates[1], coordinates[2]);
        return true;
    }

    static DistanceMethod? GetDistanceMethod()
    {
        while (true)
        {
            Console.WriteLine($"Choose the method: {Environment.NewLine}1 - Euclidean Distance{Environment.NewLine}2 - Manhattan Distance");
            var input = Console.ReadLine();
            switch (input)
            {
                case "1":
                    return DistanceMethod.Euclidean;
                case "2":
                    return DistanceMethod.Manhattan;
                default:
                    Console.WriteLine($"Incorrect Input! Please use \"1\" for the euclidean distance or \"2\" for the manhattan distance an!{Environment.NewLine}");
                    break;
            }
        }
    }
}
