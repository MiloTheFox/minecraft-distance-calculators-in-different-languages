using System;

class DistanceCalculator
{
    public class Point3D(double x, double y, double z)
    {
        public double X { get; } = x;
        public double Y { get; } = y;
        public double Z { get; } = z;
    }

    public enum DistanceMethod
    {
        Euclidean,
        Manhattan
    }

    static void Main()
    {
        try
        {
            var point1 = GetPointFromUser("Please provide the first point (x y z): ");
            var point2 = GetPointFromUser("Please provide the second point (x y z): ");
            var choice = GetDistanceMethod();

            double distance = CalculateDistance(point1, point2, choice);
            Console.WriteLine($"The {(choice == DistanceMethod.Euclidean ? "Euclidean" : "Manhattan")} distance is: {distance:F2}");
        }
        catch (Exception ex)
        {
            Console.WriteLine($"An error occurred: {ex.Message}");
        }
    }

    static double CalculateDistance(Point3D point1, Point3D point2, DistanceMethod method)
    {
        return method switch
        {
            DistanceMethod.Euclidean => Math.Sqrt(Math.Pow(point1.X - point2.X, 2) + Math.Pow(point1.Y - point2.Y, 2) + Math.Pow(point1.Z - point2.Z, 2)),
            DistanceMethod.Manhattan => Math.Abs(point1.X - point2.X) + Math.Abs(point1.Y - point2.Y) + Math.Abs(point1.Z - point2.Z),
            _ => throw new InvalidOperationException("This distance method is not existent yet!")
        };
    }

    static Point3D GetPointFromUser(string prompt)
    {
        while (true)
        {
            Console.Write(prompt);
            string input = Console.ReadLine() ?? string.Empty;
            if (TryParsePoint(input, out var point) && point != null)
                return point;

            Console.WriteLine("Incorrect input! Please provide a total of 3 numbers separated by spaces.");
        }
    }

    static bool TryParsePoint(string input, out Point3D? point)
    {
        var parts = input.Split(' ', StringSplitOptions.RemoveEmptyEntries);
        if (parts.Length == 3 &&
            double.TryParse(parts[0], out var x) &&
            double.TryParse(parts[1], out var y) &&
            double.TryParse(parts[2], out var z))
        {
            point = new Point3D(x, y, z);
            return true;
        }

        point = null;
        return false;
    }

    static DistanceMethod GetDistanceMethod()
    {
        while (true)
        {
            Console.WriteLine("Choose the method:\n1 - Euclidean Distance\n2 - Manhattan Distance");
            var input = Console.ReadLine()?.Trim().ToLower();
            switch (input)
            {
                case "euclidean":
                    return DistanceMethod.Euclidean;
                case "manhattan":
                    return DistanceMethod.Manhattan;
                default:
                    Console.WriteLine("Incorrect input! Please use \"euclidean\" or \"manhattan\".");
                    break;
            }
        }
    }
}
