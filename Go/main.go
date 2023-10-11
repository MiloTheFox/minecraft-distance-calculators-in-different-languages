package main

import (
	"fmt"
	"math"
	"log"
)

type Point struct {
	X, Y, Z float64
}

// Constants for distance calculation methods
const (
	Euclidean = "euclidean"
	Manhattan = "manhattan"
)

func main() {
	point1 := getPoint("Enter the coordinates of Point 1 (X Y Z):")
	point2 := getPoint("Enter the coordinates of Point 2 (X Y Z):")

	fmt.Print("Enter the distance calculation method (euclidean or manhattan): ")
	method := getUserInput()

	var distance float64
	switch method {
	case Euclidean:
		distance = euclideanDistance(point1, point2)
	case Manhattan:
		distance = manhattanDistance(point1, point2)
	default:
		log.Fatal("Invalid method. Please enter 'euclidean' or 'manhattan'.")
	}

	fmt.Printf("Distance between Point 1 and Point 2: %f\n", distance)
}

func getPoint(prompt string) Point {
	var x, y, z float64
	fmt.Print(prompt + " ")
	_, err := fmt.Scanf("%f %f %f\n", &x, &y, &z)
	if err != nil {
		log.Fatal("Invalid input:", err)
	}
	return Point{x, y, z}
}

func getUserInput() string {
	var input string
	fmt.Scanf("%s\n", &input)
	return input
}

func euclideanDistance(p1, p2 Point) float64 {
	dx := p2.X - p1.X
	dy := p2.Y - p1.Y
	dz := p2.Z - p1.Z
	return math.RoundToEven(math.Sqrt(dx*dx + dy*dy + dz*dz))
}

func manhattanDistance(p1, p2 Point) float64 {
	dx := math.Abs(p2.X - p1.X)
	dy := math.Abs(p2.Y - p1.Y)
	dz := math.Abs(p2.Z - p1.Z)
	return math.RoundToEven(dx + dy + dz)
}