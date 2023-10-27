import * as readline from 'readline';

interface CoordinateLimits {
  X: { min: number; max: number };
  Y: { min: number; max: number };
  Z: { min: number; max: number };
}

const COORDINATE_LIMITS: CoordinateLimits = {
  X: { min: -30000000, max: 30000000 },
  Y: { min: -319, max: 319 },
  Z: { min: -30000000, max: 30000000 },
};

type Coordinates = [number, number, number];

enum DistanceMethod {
  EUCLIDEAN = 'euclidean',
  MANHATTAN = 'manhattan',
}

const rl = readline.createInterface({
  input: process.stdin,
  output: process.stdout,
});

function square(x: number): number {
  return x * x;
}

function validateCoordinateValue(value: number, limit: { min: number; max: number }): boolean {
  return value >= limit.min && value <= limit.max;
}

function validateCoordinates(coordinates: Coordinates): boolean {
  if (coordinates.length !== 3 || coordinates.some(isNaN)) {
    return false;
  }

  return Object.keys(COORDINATE_LIMITS).every((key, index) => {
    const limitKey = key as keyof CoordinateLimits;
    const value = coordinates[index];
    const limit = COORDINATE_LIMITS[limitKey];
    return validateCoordinateValue(value, limit);
  });
}

function parseCoordinates(input: string): Coordinates | null {
  const parts = input.split(' ').map(part => parseFloat(part.trim())) as Coordinates;
  return validateCoordinates(parts) ? parts : null;
}

async function promptCoordinates(promptText: string): Promise<Coordinates> {
  while (true) {
    const input = await new Promise<string>(resolve => rl.question(promptText, resolve));

    const coordinates = parseCoordinates(input);

    if (coordinates) {
      return coordinates;
    } else {
      console.error(`Invalid input. Please enter valid numbers.`);
    }
  }
}

async function promptDistanceMethod(promptText: string): Promise<DistanceMethod> {
  while (true) {
    const input = await new Promise<string>(resolve => rl.question(promptText, resolve));
    const distanceMethod = input.trim().toLowerCase() as DistanceMethod;

    
    if (distanceMethod === DistanceMethod.EUCLIDEAN || distanceMethod === DistanceMethod.MANHATTAN) {
      return distanceMethod;
    } else {
      console.error('Invalid distance method. Please choose "Euclidean" or "Manhattan".');
    }
  }
}

function calculateDistance(coords1: Coordinates, coords2: Coordinates, method: DistanceMethod): number {
  const [x1, y1, z1] = coords1;
  const [x2, y2, z2] = coords2;

  switch (method) {
    case DistanceMethod.EUCLIDEAN:
      return Math.round(Math.sqrt(square(x1 - x2) + square(y1 - y2) + square(z1 - z2));
    case DistanceMethod.MANHATTAN:
      return Math.abs(x1 - x2) + Math.abs(y1 - y2) + Math.abs(z1 - z2);
    default:
      throw new Error(`Unsupported distance method: ${method}`);
  }
}

async function main() {
  try {
    const coords1 = await promptCoordinates('Enter the first set of coordinates: ');
    const coords2 = await promptCoordinates('Enter the second set of coordinates: ');
    const distanceMethod = await promptDistanceMethod('Choose the distance method (Euclidean or Manhattan): ');

    const distance = calculateDistance(coords1, coords2, distanceMethod);
    console.log(`Distance: ${distance}`);
  } catch (error) {
    console.error(error.message);
  } finally {
    rl.close();
  }
}

main();
