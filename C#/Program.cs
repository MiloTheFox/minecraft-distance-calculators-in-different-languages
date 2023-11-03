using System;

// Definiert eine 3D-Punkt-Klasse mit X, Y und Z als Koordinaten
class Point3D
{
    public double X { get; set; }
    public double Y { get; set; }
    public double Z { get; set; }

    // Konstruktor für die Point3D-Klasse
    public Point3D(double x, double y, double z)
    {
        X = x;
        Y = y;
        Z = z;
    }
}

// Enum zur Auswahl der Distanzmethode
enum DistanceMethod
{
    Euclidean,
    Manhattan
}

class Program
{
    static void Main(string[] args)
    {
        // Eingabeaufforderung für den Benutzer zur Eingabe der Punkte
        Point3D point1 = GetPointFromUser("Geben Sie den ersten Punkt an (x y z): ");
        Point3D point2 = GetPointFromUser("Geben Sie den zweiten Punkt an (x y z): ");

        DistanceMethod? choice = null;
        do
        {
            // Eingabeaufforderung für den Benutzer zur Auswahl der Distanzmethode
            Console.WriteLine("Wählen Sie eine Methode aus: ");
            Console.WriteLine("1 - Euclidean Distanz");
            Console.WriteLine("2 - Manhattan Distanz");
            string input = Console.ReadLine() ?? string.Empty;

            // Auswahl der Distanzmethode basierend auf der Benutzereingabe
            switch (input)
            {
                case "1":
                    choice = DistanceMethod.Euclidean;
                    break;
                case "2":
                    choice = DistanceMethod.Manhattan;
                    break;
                default:
                    Console.WriteLine("Fehlerhafte Eingabe! Bitte geben Sie \"1\" für Euclidean oder \"2\" für Manhattan ein!");
                    break;
            }
        } while (!choice.HasValue);

        // Berechnung und Ausgabe der Distanz basierend auf der ausgewählten Methode
        switch (choice.Value)
        {
            case DistanceMethod.Euclidean:
                double euclideanDistance = CalculateEuclideanDistance(point1, point2);
                Console.WriteLine($"Die Euclidische Distanz zwischen den angegebenen Punkten beträgt: {euclideanDistance:F2}");
                break;
            case DistanceMethod.Manhattan:
                double manhattanDistance = CalculateManhattanDistance(point1, point2);
                Console.WriteLine($"Die Manhattan Distanz zwischen den angegebenen Punkten beträgt: {manhattanDistance:F2}");
                break;
        }
    }

    // Methode zur Eingabeaufforderung für den Benutzer zur Eingabe eines Punktes
    static Point3D GetPointFromUser(string prompt)
    {
        Console.Write(prompt);
        string? input = Console.ReadLine();
        if (input != null && TryParsePoint(input, out Point3D point))
        {
            return point;
        }
        else
        {
            Console.WriteLine("Fehlerhafte Eingabe! Bitte geben Sie 3 Zahlen, die jeweils mit einem Leerzeichen getrennt sind, an!");
            return GetPointFromUser(prompt);
        }
    }

    // Methode zur Überprüfung, ob die Benutzereingabe in einen Punkt umgewandelt werden kann
    static bool TryParsePoint(string input, out Point3D point)
    {
        point = new Point3D(0, 0, 0);

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

    // Methode zur Berechnung der euklidischen Distanz zwischen zwei Punkten
    static double CalculateEuclideanDistance(Point3D point1, Point3D point2)
    {
        double deltaX = point1.X - point2.X;
        double deltaY = point1.Y - point2.Y;
        double deltaZ = point1.Z - point2.Z;

        return Math.Sqrt(deltaX * deltaX + deltaY * deltaY + deltaZ * deltaZ);
    }

    // Methode zur Berechnung der Manhattan-Distanz zwischen zwei Punkten
    static double CalculateManhattanDistance(Point3D point1, Point3D point2)
    {
        double deltaX = Math.Abs(point1.X - point2.X);
        double deltaY = Math.Abs(point1.Y - point2.Y);
        double deltaZ = Math.Abs(point1.Z - point2.Z);

        return deltaX + deltaY + deltaZ;
    }
}
