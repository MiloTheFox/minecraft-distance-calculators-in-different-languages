import kotlin.math.abs
import kotlin.math.pow
import kotlin.math.sqrt
import kotlin.math.round

// Constants for distance methods
enum class DistanceMethod {
    EUCLIDEAN,
    MANHATTAN
}

fun main() {
    println("Enter the coordinates of the first point (x1 y1 z1):")
    val point1 = readValidPoint()

    println("Enter the coordinates of the second point (x2 y2 z2):")
    val point2 = readValidPoint()

    println("Choose the distance method (euclidean/manhattan):")
    val distanceMethod = readLine()?.trim()?.lowercase()

    val selectedMethod = when (distanceMethod) {
        "euclidean" -> DistanceMethod.EUCLIDEAN
        "manhattan" -> DistanceMethod.MANHATTAN
        else -> {
            println("Invalid distance method. Please choose either 'euclidean' or 'manhattan'.")
            return
        }
    }

    val distance = calculateDistance(point1, point2, selectedMethod)
    println("${selectedMethod.name.replaceFirstChar { it.uppercase() }} Distance: $distance")
}

data class Point(val x: Double, val y: Double, val z: Double)

fun readValidPoint(): Point {
    while (true) {
        println("Please enter 3 coordinates separated by spaces (e.g., 1.0 2.0 3.0):")
        val input = readLine() ?: ""
        val coordinates = input.split(" ").mapNotNull { it.toDoubleOrNull() }

        if (coordinates.size == 3) {
            return Point(coordinates[0], coordinates[1], coordinates[2])
        }

        println("Invalid input.")
    }
}

// Function to calculate distance based on the selected method
fun calculateDistance(point1: Point, point2: Point, method: DistanceMethod): Double {
    return when (method) {
        DistanceMethod.EUCLIDEAN -> calculateEuclideanDistance(point1, point2)
        DistanceMethod.MANHATTAN -> calculateManhattanDistance(point1, point2)
    }
}

inline fun calculateEuclideanDistance(point1: Point, point2: Point): Double {
    return round(sqrt((point1.x - point2.x).pow(2) + (point1.y - point2.y).pow(2) + (point1.z - point2.z).pow(2)))
}

inline fun calculateManhattanDistance(point1: Point, point2: Point): Double {
    return abs(point1.x - point2.x) + abs(point1.y - point2.y) + abs(point1.z - point2.z)
}
