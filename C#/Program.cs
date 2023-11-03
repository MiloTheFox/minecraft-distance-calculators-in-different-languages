using System;

class Point3D
{
    public double X { get; set; }
    public double Y { get; set; }
    public double Z { get; set; }

    public Point3D(double x, double y, double z)
    {
        X = x;
        Y = y;
        Z = z;
    }
}

class Program
{
    static void Main(string[] args)
    {
        Point3D point1 = GetPointFromUser("Enter the first point (x y z): ");
        Point3D point2 = GetPointFromUser("Enter the second point (x y z):");

        Console.WriteLine("Choose a distance method: ");
        Console.WriteLine("1 - Euclidean distance");
        Console.WriteLine("2 - Manhattan distance");
        string choice = Console.ReadLine();

        switch (choice)
        {
            case "1":
                // Call the CalculateEuclideanDistance method
                double euclideanDistance = CalculateEuclideanDistance(point1, point2);
                Console.WriteLine("Distance between the two points: " + euclideanDistance.ToString("F2"));
                break;
            case "2":
                // Call the CalculateManhattanDistance method
                double manhattanDistance = CalculateManhattanDistance(point1, point2);
                Console.WriteLine("Manhattan distance between the two points: " + manhattanDistance.ToString("F2"));
                break;
            default:
                Console.WriteLine("Invalid choice. Please enter 1 or 2.");
                break;
        }
    }

    static Point3D GetPointFromUser(string prompt)
    {
        Console.Write(prompt);
        if (TryParsePoint(Console.ReadLine(), out Point3D point))
        {
            return point;
        }
        else
        {
            Console.WriteLine("Invalid input. Please enter three space-separated numbers.");
            return GetPointFromUser(prompt);
        }
    }

    static bool TryParsePoint(string input, out Point3D point)
    {
        point = null;

        string[] parts = input.Split(' ');
        if (parts.Length != 3)
        {
            return false;
        }

        if (double.TryParse(parts[0], out double x) &&
            double.TryParse(parts[1], out double y) &&
            double.TryParse(parts[2], out double z))
        {
            point = new Point3D(x, y, z);
            return true;
        }

        return false;
    }

    static double CalculateEuclideanDistance(Point3D point1, Point3D point2)
    {
        double deltaX = point1.X - point2.X;
        double deltaY = point1.Y - point2.Y;
        double deltaZ = point1.Z - point2.Z;

        return Math.Sqrt(deltaX * deltaX + deltaY * deltaY + deltaZ * deltaZ);
    }

    static double CalculateManhattanDistance(Point3D point1, Point3D point2)
    {
        double deltaX = Math.Abs(point1.X - point2.X);
        double deltaY = Math.Abs(point1.Y - point2.Y);
        double deltaZ = Math.Abs(point1.Z - point2.Z);

        return deltaX + deltaY + deltaZ;
    }
}