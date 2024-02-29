import java.util.Arrays;
import java.util.Scanner;

class DeepString {
    public static void main(String[] args) {
        int[][] a = {{1}, {2, 3}, {4, 5, 6}};
        for(int[] linie:a) {
            for (int elem : linie) {
                System.out.print(elem + " ");
            }
            System.out.print("\n");
        }
        System.out.print(Arrays.deepToString(a));
    }
}

class Compare {
    public static void main(String[] args) {
        int[] t = {1, 2, 3, 4, 5};
        int[] u = {1, 2, 3};
        int[] v = {1, 2, 3, 4, 5};
        int[] w = {1, 2, 4, 4, 5};

        System.out.println(Arrays.compare(t,v)); // 0
        System.out.println(Arrays.compare(t,u)); // > 0
        System.out.println(Arrays.compare(w,v)); // > 0
        System.out.println(Arrays.compare(v,w)); // < 0
    }
}

class ArraysOther{
    public static void main(String[] args){
        int[] a = {1,5,2,6,8,2,4};
        int[] b = {1,7,3,2,6,1,2,5};
        Arrays.fill(a,1);
        System.out.println(Arrays.equals(a,b));
        System.out.println(Arrays.mismatch(a,b));
        System.out.println(Arrays.compare(a,b));
    }
}

class Copy {
    public static void main(String[] args) {
        int[] t = {1, 2, 3, 4, 5};
        int[] u = Arrays.copyOf(t, t.length);
        int[] v = Arrays.copyOf(t, 3);
        int[] w = Arrays.copyOf(t, 8);

        System.out.println(Arrays.toString(u));
        System.out.println(Arrays.toString(v));
        System.out.println(Arrays.toString(w));
    }
}

class MergeSort {
    public static void Sort(int[] array) {
        if (array.length <= 1) {
            return;
        }

        int mid = array.length / 2;
        int[] left = new int[mid];
        int[] right = new int[array.length - mid];

        System.arraycopy(array, 0, left, 0, left.length);
        System.arraycopy(array, mid, right, 0, right.length);

        Sort(left);
        Sort(right);
        merge(array, left, right);
    }

    private static void merge(int[] array, int[] left, int[] right) {
        int i = 0, j = 0, k = 0;

        while (i < left.length && j < right.length) {
            if (left[i] <= right[j]) {
                array[k++] = left[i++];
            } else {
                array[k++] = right[j++];
            }
        }

        while (i < left.length) {
            array[k++] = left[i++];
        }

        while (j < right.length) {
            array[k++] = right[j++];
        }
    }

    public static void main(String[] args) {
        int[] array = {12, 11, 13, 5, 6, 7};

        Sort(array);

        System.out.println("Sorted array: " + Arrays.toString(array));
    }
}

class BinarySearch {
    public static int binarySearch(int[] array, int target) {
        int left = 0;
        int right = array.length - 1;

        while (left <= right) {
            int mid = left + (right - left) / 2;

            if (array[mid] == target) {
                return mid;
            } else if (array[mid] < target) {
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }

        return -1;
    }

    public static void main(String[] args) {
        int[] sortedArray = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
        int target = 7;

        int result = binarySearch(sortedArray, target);

        if (result != -1) {
            System.out.println("Element " + target + " found at index " + result);
        } else {
            System.out.println("Element " + target + " not found in the array");
        }
    }
}
public class Main {
    static long factorial(int n) {
        long result = 1;
        for (int i = 1; i <= n; i++) {
            result *= i;
        }

        return result;
    }

    public static void main(String[] args) {
        Scanner read = new Scanner(System.in);
        System.out.println("Enter number: ");
        int n = read.nextInt();
        read.close();

        System.out.println("Rezultat: " + factorial(n));
    }
}