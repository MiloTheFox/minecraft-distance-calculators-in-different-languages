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

        double distance = CalculateDistance(point1, point2);

        Console.WriteLine("Distance between the two points: " + distance.ToString("F2"));
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

    static double CalculateDistance(Point3D point1, Point3D point2)
    {
        double deltaX = point1.X - point2.X;
        double deltaY = point1.Y - point2.Y;
        double deltaZ = point1.Z - point2.Z;

        return Math.Sqrt(deltaX * deltaX + deltaY * deltaY + deltaZ * deltaZ);
    }
}