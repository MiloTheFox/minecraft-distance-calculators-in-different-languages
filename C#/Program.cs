class DistanceCalculator
{
    // Definiert eine 3D-Punkt-Klasse mit X, Y und Z als Koordinaten
    public class Point3D(double x, double y, double z)
    {
        public double X { get; } = x;
        public double Y { get; } = y;
        public double Z { get; } = z;
    }
    
    // Enum zur Auswahl der Distanzmethode
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

        // Auswahl der Distanzmethode basierend auf der Benutzereingabe
        var distance = choice switch
        {
            // Berechnung der Euklidischen Distanz zwischen zwei Punkten
            DistanceMethod.Euclidean => CalculateEuclideanDistance(in point1, in point2),
            // Berechnung der Manhattan Distanz zwischen zwei Punkten
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

    // Methode zur Überprüfung, ob die Benutzereingabe in einen Punkt umgewandelt werden kann
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
            // Eingabeaufforderung für den Benutzer zur Auswahl der Distanzmethode
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
