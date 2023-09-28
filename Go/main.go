package main

import (
	"fmt"
	"math"
	"os"
	"strings"
)

type Point struct {
	X, Y, Z float64
}

type DistanceFunc func(p1, p2 Point) float64

var distanceFuncs = map[string]DistanceFunc{
	"euclidean": euclideanDistance,
	"manhattan": manhattanDistance,
}

func main() {
	defer func() {
		if err := recover(); err != nil {
			fmt.Fprintf(os.Stderr, "Error: %v\n", err)
		}
	}()

	point1 := getPoint("Enter the coordinates of Point 1 (X Y Z):")
	point2 := getPoint("Enter the coordinates of Point 2 (X Y Z):")

	fmt.Print("Enter the distance calculation method (euclidean or manhattan): ")
	var method string
	fmt.Scan(&method)

	distanceFunc, ok := distanceFuncs[strings.ToLower(method)]
	if !ok {
		panic("Invalid method. Please enter 'euclidean' or 'manhattan'.")
	}

	distance := distanceFunc(point1, point2)
	fmt.Printf("Distance between Point 1 and Point 2: %f\n", distance)
}

func getPoint(prompt string) Point {
	var x, y, z float64
	fmt.Print(prompt + " ")
	n, err := fmt.Scan(&x, &y, &z)
	if err != nil || n != 3 {
		panic(fmt.Sprintf("invalid input: %v", err))
	}
	return Point{x, y, z}
}

func euclideanDistance(p1, p2 Point) float64 {
	dx := p2.X - p1.X
	dy := p2.Y - p1.Y
	dz := p2.Z - p1.Z
	return math.Round(math.Sqrt(dx*dx + dy*dy + dz*dz))
}

func manhattanDistance(p1, p2 Point) float64 {
	dx := math.Abs(p2.X - p1.X)
	dy := math.Abs(p2.Y - p1.Y)
	dz := math.Abs(p2.Z - p1.Z)
	return math.Round(dx + dy + dz)
}
