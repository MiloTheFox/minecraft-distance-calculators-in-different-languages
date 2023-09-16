package main

import (
	"fmt"
	"math"
	"os"
	"strings"
)

// Point represents a 3D point in Minecraft coordinates.
type Point struct {
	X, Y, Z float64
}

func main() {
	// Get the coordinates of Point 1
	point1, err := getPoint("Enter the coordinates of Point 1 (X Y Z):")
	if err != nil {
		fmt.Println("Error:", err)
		return
	}

	// Get the coordinates of Point 2
	point2, err := getPoint("Enter the coordinates of Point 2 (X Y Z):")
	if err != nil {
		fmt.Println("Error:", err)
		return
	}

	// Prompt the user to select the distance calculation method
	fmt.Print("Enter the distance calculation method (euclidean or manhattan): ")
	var method string
	_, err = fmt.Scan(&method)
	if err != nil {
		fmt.Fprintf(os.Stderr, "Invalid input. Please enter 'euclidean' or 'manhattan'.")
		return
	}

	var distance float64

	switch strings.ToLower(method) {
	case "euclidean":
		distance = euclideanDistance(point1, point2)
		fmt.Fprintf(os.Stdout, "Euclidean Distance between Point 1 and Point 2: %f\n", distance)
	case "manhattan":
		distance = manhattanDistance(point1, point2)
		fmt.Fprintf(os.Stdout, "Manhattan Distance between Point 1 and Point 2: %f\n", distance)
	default:
		fmt.Fprintf(os.Stderr, "Invalid method. Please enter 'euclidean' or 'manhattan'.")
	}
}

// getPoint reads coordinates from the user and returns an error on failure.
func getPoint(prompt string) (Point, error) {
	var x, y, z float64
	fmt.Print(prompt + " ")
	_, err := fmt.Scan(&x, &y, &z)
	if err != nil {
		return Point{}, fmt.Errorf("invalid input: %v", err)
	}
	return Point{x, y, z}, nil
}

// euclideanDistance calculates the Euclidean distance between two points.
func euclideanDistance(p1, p2 Point) float64 {
	dx := p2.X - p1.X
	dy := p2.Y - p1.Y
	dz := p2.Z - p1.Z
	return math.Round(math.Sqrt(dx*dx + dy*dy + dz*dz))
}

// manhattanDistance calculates the Manhattan distance between two points.
func manhattanDistance(p1, p2 Point) float64 {
	dx := math.Abs(p2.X - p1.X)
	dy := math.Abs(p2.Y - p1.Y)
	dz := math.Abs(p2.Z - p1.Z)
	return math.Round(dx + dy + dz)
}
