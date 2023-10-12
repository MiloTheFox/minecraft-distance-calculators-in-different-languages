// Import readline module
import * as readline from 'readline';

// Create an interface for the coordinate limits
interface CoordinateLimits {
    X: { min: number; max: number };
    Y: { min: number; max: number };
    Z: { min: number; max: number };
}

// Define the coordinate limits as constants
const COORDINATE_LIMITS: CoordinateLimits = {
    X: { min: -30000000, max: 30000000 },
    Y: { min: -319, max: 319 },
    Z: { min: -30000000, max: 30000000 },
};

// Define a type alias for the coordinates
type Coordinates = [number, number, number];

// Define an enum for the distance methods
enum DistanceMethod {
    EUCLIDEAN = 'euclidean',
    MANHATTAN = 'manhattan',
}

// Create a readline interface
const rl = readline.createInterface({
    input: process.stdin,
    output: process.stdout,
});

// Function to calculate the square of a number
function square(x: number): number {
    return x * x;
}

// Function to calculate the absolute value of a number
function abs(x: number): number {
    return x < 0 ? -x : x;
}

// Function to calculate the Euclidean distance between two coordinates
function calculateEuclideanDistance(coords1: Coordinates, coords2: Coordinates): number {
    // Destructure the coordinates into variables
    const [x1, y1, z1] = coords1;
    const [x2, y2, z2] = coords2;

    // Calculate the difference along each axis
    const dx = x1 - x2;
    const dy = y1 - y2;
    const dz = z1 - z2;

    // Return the rounded square root of the sum of squares
    return Math.round(Math.sqrt(square(dx) + square(dy) + square(dz)));
}

// Function to calculate the Manhattan distance between two coordinates
function calculateManhattanDistance(coords1: Coordinates, coords2: Coordinates): number {
    // Destructure the coordinates into variables
    const [x1, y1, z1] = coords1;
    const [x2, y2, z2] = coords2;

    // Calculate the absolute difference along each axis
    const dx = abs(x1 - x2);
    const dy = abs(y1 - y2);
    const dz = abs(z1 - z2);

    // Return the sum of absolute differences
    return dx + dy + dz;
}

// Function to validate a coordinate value against a limit
function validateCoordinateValue(value: number, limit: { min: number; max: number }): boolean {
    // Check if the value is within the range of the limit
    return value >= limit.min && value <= limit.max;
}

// Function to validate a coordinate array against the coordinate limits
function validateCoordinates(coordinates: Coordinates): boolean {
    // Check if the array has three elements and they are all numbers
    if (coordinates.length !== 3 || coordinates.some(isNaN)) {
        return false;
    }

    // Check if each coordinate value is within the corresponding limit
    return Object.keys(COORDINATE_LIMITS).every((key, index) => {
        // Cast the key to a keyof type to access the limit object
        const limitKey = key as keyof CoordinateLimits;

        // Get the coordinate value and the limit object
        const value = coordinates[index];
        const limit = COORDINATE_LIMITS[limitKey];

        // Validate the coordinate value against the limit
        return validateCoordinateValue(value, limit);
    });
}

// Function to parse and validate an input string into a coordinate array
function parseCoordinates(input: string): Coordinates | null {
    // Split the input by spaces and trim any whitespace
    const parts = input.split(' ').map((part) => part.trim());

    // Parse each part into a number and store in an array
    const coordinates = parts.map((part) => parseFloat(part)) as Coordinates;

    // Validate the coordinates and return them or null if invalid
    return validateCoordinates(coordinates) ? coordinates : null;
}

// Function to prompt for coordinates using a given text
async function promptCoordinates(promptText: string): Promise<Coordinates> {
    // Wrap the readline question in a promise
    return new Promise((resolve, reject) => {
        rl.question(promptText, (input) => {
            // Parse and validate the input into coordinates or null if invalid
            const coordinates = parseCoordinates(input);

            if (coordinates) {
                // Resolve the promise with the valid coordinates
                resolve(coordinates);
            } else {
                // Reject the promise with an error message and exit code
                reject(
                    new Error(
                        `Invalid input. Please enter valid numbers for X (${COORDINATE_LIMITS.X.min} - ${COORDINATE_LIMITS.X.max}), Y (${COORDINATE_LIMITS.Y.min} - ${COORDINATE_LIMITS.Y.max}), and Z (${COORDINATE_LIMITS.Z.min} - ${COORDINATE_LIMITS.Z.max}).`
                    )
                );
                process.exit(1); // Exit the program on invalid input
            }
        });
    });
}

// Function to prompt for a distance method using a given text
async function promptDistanceMethod(promptText: string): Promise<DistanceMethod> {
    // Wrap the readline question in a promise
    return new Promise((resolve) => {
        rl.question(promptText, (input) => {
            // Trim and lowercase the input and cast it to a distance method type
            const distanceMethod = input.trim().toLowerCase() as DistanceMethod;

            // Use a try-catch block to handle errors
            try {
                // Check if the distance method is valid
                if (distanceMethod === DistanceMethod.EUCLIDEAN || distanceMethod === DistanceMethod.MANHATTAN) {
                    // Resolve the promise with the valid distance method
                    resolve(distanceMethod);
                } else {
                    // Throw a custom error with a message
                    throw new Error('Invalid distance method. Please choose "Euclidean" or "Manhattan".');
                }
            } catch (e: unknown) { // <-- note `e` has explicit `unknown` type
                // Check if the error is an instance of Error
                if (e instanceof Error) {
                    // Print the error message to the console
                    console.error(e.message);
                } else {
                    // Handle other types of errors
                    console.error('An unexpected error occurred.');
                }
            }
        });
    });
}

// Function to calculate the distance between two coordinates using a given method
function calculateDistance(coords1: Coordinates, coords2: Coordinates, method: DistanceMethod): number {
    // Use a switch statement to handle different methods
    switch (method) {
        case DistanceMethod.EUCLIDEAN:
            // Return the Euclidean distance
            return calculateEuclideanDistance(coords1, coords2);
        case DistanceMethod.MANHATTAN:
            // Return the Manhattan distance
            return calculateManhattanDistance(coords1, coords2);
        default:
            // Throw an error if the method is not supported
            throw new Error(`Unsupported distance method: ${method}`);
    }
}

// The main function of the program
async function main() {
    try {
        // Prompt for the first set of coordinates
        const coords1 = await promptCoordinates('Enter the first set of coordinates: ');

        // Prompt for the second set of coordinates
        const coords2 = await promptCoordinates('Enter the second set of coordinates: ');

        // Prompt for the distance method
        const distanceMethod = await promptDistanceMethod('Choose the distance method (Euclidean or Manhattan): ');

        // Calculate the distance between the coordinates using the method
        const distance = calculateDistance(coords1, coords2, distanceMethod);

        // Print the distance to the console
        console.log(`Distance: ${distance}`);
    } catch (error) {
        // Handle any errors that may occur
        console.error(error.message);
    } finally {
        // Close the readline interface
        rl.close();
    }
}

// Invoke the main function
main();