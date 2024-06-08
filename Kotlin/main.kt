import kotlin.math.*

// Constants for distance methods
enum class DistanceMethod {
    EUCLIDEAN,
    MANHATTAN
}

fun main() {
    val point1 = readValidPoint("first")
    val point2 = readValidPoint("second")
    val selectedMethod = readDistanceMethod()

    val distance = calculateDistance(point1, point2, selectedMethod)
    println("${selectedMethod.name.replaceFirstChar { it.uppercase() }} Distance: $distance")
}

data class Point(val x: Double, val y: Double, val z: Double)

fun readValidPoint(order: String): Point {
    while (true) {
        println("Enter the coordinates of the $order point (x y z):")
        val input = readLine()
        if (input != null) {
            val coordinates = input.split("\\s+".toRegex()).mapNotNull { it.toDoubleOrNull() }
            if (coordinates.size == 3) {
                return Point(coordinates[0], coordinates[1], coordinates[2])
            }
        }
        println("Invalid input. Please enter exactly 3 numeric coordinates separated by spaces (e.g., 1.0 2.0 3.0).")
    }
}

fun readDistanceMethod(): DistanceMethod {
    while (true) {
        println("Choose the distance method (euclidean/manhattan):")
        val input = readLine()?.uppercase()
        try {
            return DistanceMethod.valueOf(input ?: "")
        } catch (e: IllegalArgumentException) {
            println("Invalid input. Please enter 'euclidean' or 'manhattan'.")
        }
    }
}

// Function to calculate distance based on the selected method
fun calculateDistance(point1: Point, point2: Point, method: DistanceMethod): Double {
    return when (method) {
        DistanceMethod.EUCLIDEAN -> calculateEuclideanDistance(point1, point2)
        DistanceMethod.MANHATTAN -> calculateManhattanDistance(point1, point2)
    }
}

fun calculateEuclideanDistance(point1: Point, point2: Point): Double {
    return sqrt((point1.x - point2.x).pow(2) + (point1.y - point2.y).pow(2) + (point1.z - point2.z).pow(2))
}

fun calculateManhattanDistance(point1: Point, point2: Point): Double {
    return abs(point1.x - point2.x) + abs(point1.y - point2.y) + abs(point1.z - point2.z)
}
