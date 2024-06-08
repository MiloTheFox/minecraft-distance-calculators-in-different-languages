// main.go
package main

import (
	"bufio"
	"fmt"
	"math"
	"os"
	"strings"

	"golang.org/x/text/cases"
	"golang.org/x/text/language"
)

type Point struct {
	X, Y, Z float64
}

const (
	Euclidean = "euclidean"
	Manhattan = "manhattan"
)

func titleCase(s string) string {
	return cases.Title(language.English).String(s)
}

func main() {
	reader := bufio.NewReader(os.Stdin)
	point1 := getPoint(reader, "Enter the coordinates of Point 1 (X Y Z):")
	point2 := getPoint(reader, "Enter the coordinates of Point 2 (X Y Z):")
	method := getCalculationMethod(reader)

	var distance float64
	switch method {
	case Euclidean:
		distance = calculateDistance(point1, point2, euclideanDistance)
	case Manhattan:
		distance = calculateDistance(point1, point2, manhattanDistance)
	default:
		fmt.Println("Invalid method. Please enter 'euclidean' or 'manhattan'.")
		return
	}
	fmt.Printf("%s Distance between Point 1 and Point 2: %.2f\n", titleCase(method), distance)
}

func getPoint(reader *bufio.Reader, prompt string) Point {
	var x, y, z float64
	for {
		fmt.Print(prompt + " ")
		line, _ := reader.ReadString('\n')
		n, err := fmt.Sscanf(line, "%f %f %f", &x, &y, &z)
		if err == nil && n == 3 {
			return Point{x, y, z}
		}
		fmt.Println("Invalid input. Please enter valid coordinates.")
	}
}

func getCalculationMethod(reader *bufio.Reader) string {
	for {
		fmt.Print("Enter the distance calculation method (euclidean or manhattan): ")
		method := strings.ToLower(getUserInput(reader))
		if method == Euclidean || method == Manhattan {
			return method
		}
		fmt.Println("Invalid method. Please enter 'euclidean' or 'manhattan'.")
	}
}

func getUserInput(reader *bufio.Reader) string {
	input, _ := reader.ReadString('\n')
	return strings.TrimSpace(input)
}

func calculateDistance(p1, p2 Point, distFunc func(Point, Point) float64) float64 {
	return distFunc(p1, p2)
}

func euclideanDistance(p1, p2 Point) float64 {
	dx := p2.X - p1.X
	dy := p2.Y - p1.Y
	dz := p2.Z - p1.Z
	return math.Hypot(dx, math.Hypot(dy, dz))
}

func manhattanDistance(p1, p2 Point) float64 {
	dx := math.Abs(p2.X - p1.X)
	dy := math.Abs(p2.Y - p1.Y)
	dz := math.Abs(p2.Z - p1.Z)
	return dx + dy + dz
}
