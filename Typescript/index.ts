import * as readline from 'readline';
import { promisify } from 'util';

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

const questionAsync = promisify(rl.question).bind(rl);

function parseAndValidateCoordinates(input: string): Coordinates | null {
  const parts = input.split(' ').map(Number);

  if (parts.length !== 3 || parts.some(isNaN)) {
    return null;
  }

  const [x, y, z] = parts;

  if (
    x >= COORDINATE_LIMITS.X.min && x <= COORDINATE_LIMITS.X.max &&
    y >= COORDINATE_LIMITS.Y.min && y <= COORDINATE_LIMITS.Y.max &&
    z >= COORDINATE_LIMITS.Z.min && z <= COORDINATE_LIMITS.Z.max
  ) {
    return [x, y, z];
  } else {
    return null;
  }
}

async function promptCoordinates(promptText: string): Promise<Coordinates> {
  while (true) {
    const input = await questionAsync(promptText);
    const coordinates = parseAndValidateCoordinates(input);

    if (coordinates) {
      return coordinates;
    } else {
      console.error(`Invalid input. Please enter valid numbers within the limits: X(${COORDINATE_LIMITS.X.min}, ${COORDINATE_LIMITS.X.max}), Y(${COORDINATE_LIMITS.Y.min}, ${COORDINATE_LIMITS.Y.max}), Z(${COORDINATE_LIMITS.Z.min}, ${COORDINATE_LIMITS.Z.max}).`);
    }
  }
}

async function promptDistanceMethod(promptText: string): Promise<DistanceMethod> {
  while (true) {
    const input = await questionAsync(promptText);
    const distanceMethod = input.trim().toLowerCase();

    if (distanceMethod === DistanceMethod.EUCLIDEAN || distanceMethod === DistanceMethod.MANHATTAN) {
      return distanceMethod as DistanceMethod;
    } else {
      console.error('Invalid distance method. Please choose "euclidean" or "manhattan".');
    }
  }
}

function calculateDistance(coords1: Coordinates, coords2: Coordinates, method: DistanceMethod): number {
  const [x1, y1, z1] = coords1;
  const [x2, y2, z2] = coords2;

  switch (method) {
    case DistanceMethod.EUCLIDEAN:
      return Math.hypot(x1 - x2, y1 - y2, z1 - z2);
    case DistanceMethod.MANHATTAN:
      return Math.abs(x1 - x2) + Math.abs(y1 - y2) + Math.abs(z1 - z2);
    default:
      throw new Error('Unknown distance method');
  }
}

async function main() {
  try {
    const coords1 = await promptCoordinates('Enter the first set of coordinates: ');
    const coords2 = await promptCoordinates('Enter the second set of coordinates: ');
    const distanceMethod = await promptDistanceMethod('Choose the distance method (euclidean or manhattan): ');

    const distance = calculateDistance(coords1, coords2, distanceMethod);
    console.log(`Distance: ${distance.toFixed(2)}`);
  } catch (error) {
    console.error(`Error: ${error.message}`);
  } finally {
    rl.close();
  }
}

main();
