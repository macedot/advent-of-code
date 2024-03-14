package main

import (
	"bufio"
	"fmt"
	"os"
	"slices"
	"sort"
	"strconv"
)

func main() {
	tot := 0
	totals := []int{0}
	scanner := bufio.NewScanner(os.Stdin)
	for scanner.Scan() {
		line := scanner.Text()
		if line == "" {
			totals = append(totals, tot)
			tot = 0
		} else {
			num, _ := strconv.Atoi(line)
			tot += num
		}
	}
	totals = append(totals, tot)

	fmt.Println("1,", slices.Max(totals))
	sort.Ints(totals)
	reverse(totals)
	fmt.Println("2,", sum(totals[:3]), totals[:3])
}

func sum(nums []int) int {
	sum := 0
	for _, num := range nums {
		sum += num
	}
	return sum
}

func reverse(nums []int) {
	for i, j := 0, len(nums)-1; i < j; i, j = i+1, j-1 {
		nums[i], nums[j] = nums[j], nums[i]
	}
}
