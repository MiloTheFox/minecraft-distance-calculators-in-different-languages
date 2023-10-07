import * as readline from 'readline';

const rl = readline.createInterface({
  input: process.stdin,
  output: process.stdout,
});

// Constants for the Limitations
const LIMITS = {
  X: { min: -30000000, max: 30000000 },
  Y: { min: -319, max: 319 },
  Z: { min: -30000000, max: 30000000 },
};

// Enum for distance methods
enum DistanceMethod {
  EUCLIDEAN = 'euclidean',
  MANHATTAN = 'manhattan',
}

// Function to calculate Euclidean Distance
function calculateEuclideanDistance(coords1: number[], coords2: number[]): number {
  const [x1, y1, z1] = coords1;
  const [x2, y2, z2] = coords2;
  const dx = x1 - x2;
  const dy = y1 - y2;
  const dz = z1 - z2;
  return Math.round(Math.sqrt(dx * dx + dy * dy + dz * dz));
}

// Function to calculate Manhattan Distance
function calculateManhattanDistance(coords1: number[], coords2: number[]): number {
  const [x1, y1, z1] = coords1;
  const [x2, y2, z2] = coords2;
  const dx = Math.abs(x1 - x2);
  const dy = Math.abs(y1 - y2);
  const dz = Math.abs(z1 - z2);
  return dx + dy + dz;
}

// Function to prompt for coordinates
async function promptCoordinates(promptText: string): Promise<number[]> {
  return new Promise((resolve, reject) => {
    rl.question(promptText, (input) => {
      const coordinates = input
        .trim()
        .split(' ')
        .map((coord) => parseFloat(coord.trim()));

      if (
        coordinates.length === 3 &&
        coordinates.every((coord) => !isNaN(coord)) &&
        validateCoordinateRange(coordinates)
      ) {
        resolve(coordinates);
      } else {
        reject(new Error(`Invalid input. Please enter three space-separated numbers within the limits.`));
      }
    });
  });
}

// Function to validate coordinate range
function validateCoordinateRange(coords: number[]): boolean {
  return coords.every((coord, index) => coord >= LIMITS[Object.keys(LIMITS)[index]].min && coord <= LIMITS[Object.keys(LIMITS)[index]].max);
}

async function main() {
  try {
    const coords1 = await promptCoordinates(`Enter the first set of coordinates: `);
    const coords2 = await promptCoordinates(`Enter the second set of coordinates: `);

    const distanceMethod = await new Promise<DistanceMethod>((resolve) => {
      rl.question('Choose the distance method (Euclidean or Manhattan): ', (method) => {
        resolve(method.trim().toLowerCase() as DistanceMethod);
      });
    });

    let distance: number;

    if (distanceMethod === DistanceMethod.EUCLIDEAN) {
      distance = calculateEuclideanDistance(coords1, coords2);
    } else if (distanceMethod === DistanceMethod.MANHATTAN) {
      distance = calculateManhattanDistance(coords1, coords2);
    } else {
      throw new Error('Invalid distance method. Please choose "Euclidean" or "Manhattan".');
    }

    console.log(`Distance: ${distance}`);
  } catch (error) {
    console.error(error);
  } finally {
    rl.close();
  }
}

main();
