import pandas
import matplotlib.pyplot as plt
from typing import List, Any


class InterpolationUtils:
    @staticmethod
    def read_data_file(file_path: str, x_column_name: str, y_column_name: str) -> (int, int):
        data = pandas.read_csv(file_path)
        return data[x_column_name].tolist(), data[y_column_name].tolist()
    @staticmethod
    def create_list_of_numbers(start: Any, end: Any, number: int) -> List[Any]:
        step = (end - start) / (number - 1)
        return [start + step * i for i in range(number)]

    @staticmethod
    def lagrange(org_x: List[Any], org_y: List[Any], interpolate_x: List[Any]) -> List[Any]:
        no_of_org_points: int = len(org_x)
        no_of_interpolation_points: int = len(interpolate_x)

        interpolate_y = [0] * no_of_interpolation_points

        for i in range(no_of_org_points):
            for j in range(no_of_interpolation_points):
                # F(x) = sum(yi * phi(x))
                interpolate_y[j] += org_y[i] * InterpolationUtils.__lagrange_phi(interpolate_x[j], org_x, i)

        return interpolate_y

    @staticmethod
    def __lagrange_phi(curr_x: Any, org_x: List[Any], i: int) -> Any:
        no_of_org_points: int = len(org_x)
        fi_i = 1

        # phi_i = sum( (x - xj) / (xi - xj) )
        for j in range(no_of_org_points):
            if j != i:
                fi_i *= (curr_x - org_x[j]) / (org_x[i] - org_x[j])

        return fi_i

    @staticmethod
    def cubic_spline(org_x: List[Any], org_y: List[Any], interpolate_x: List[Any]) -> List[Any]:
        no_of_org_points: int = len(org_x)
        no_of_interpolation_points: int = len(interpolate_x)
        interpolate_y = [0] * no_of_interpolation_points

        n = no_of_org_points - 1
        h = [org_x[i + 1] - org_x[i] for i in range(n)]
        alpha = [0] + [3 * (org_y[i + 1] - org_y[i]) / h[i] - 3 * (org_y[i] - org_y[i - 1]) / h[i - 1] for i in range(1, n)] + [0]

        l = [1] + [0] * n
        mu = [0] * n
        z = [0] * (n + 1)

        for i in range(1, n):
            l[i] = 2 * (org_x[i + 1] - org_x[i - 1]) - h[i - 1] * mu[i - 1]
            mu[i] = h[i] / l[i]
            z[i] = (alpha[i] - h[i - 1] * z[i - 1]) / l[i]

        l[n] = 1
        z[n] = 0
        a = org_y[:n]
        b = [0] * n
        c = [0] * (n + 1)
        d = [0] * n

        for j in range(n - 1, -1, -1):
            c[j] = z[j] - mu[j] * c[j + 1]
            b[j] = (org_y[j + 1] - org_y[j]) / h[j] - h[j] * (c[j + 1] + 2 * c[j]) / 3
            d[j] = (c[j + 1] - c[j]) / (3 * h[j])

        j = 0
        for x in interpolate_x:
            for i in range(n):
                if org_x[i] <= x <= org_x[i] + h[i]:
                    dx = x - org_x[i]
                    interpolate_y[j] = a[i] + b[i] * dx + c[i] * dx ** 2 + d[i] * dx ** 3
                    j += 1
                    break

        return interpolate_y


class Interpolation:
    def __init__(self, file: str):
        self.x_col, self.y_col = InterpolationUtils.read_data_file(file, "Dystans (m)", "Wysokość (m)")

    def show_plot(self, no_of_points_list: List[int]) -> None:
        no_of_plots = len(no_of_points_list)
        fig, axs = plt.subplots(no_of_plots, 2, figsize=(22, 6 * no_of_plots))
        i = 0

        for no_of_points in no_of_points_list:
            interpolate_x_lagrange, interpolate_y_lagrange, org_x_lagrange, org_y_lagrange = self.__call_interpolation_method(no_of_points, InterpolationUtils.lagrange)
            interpolate_x_cubic_splines, interpolate_y_cubic_splines, org_x_cubic_splines, org_y_cubic_splines = self.__call_interpolation_method(no_of_points, InterpolationUtils.cubic_spline)

            # Data
            axs[i, 0].scatter(self.x_col, self.y_col, label='Original', color='red', s=5)
            axs[i, 0].plot(interpolate_x_lagrange, interpolate_y_lagrange, label='Interpolation', color='green')
            axs[i, 0].scatter(org_x_lagrange, org_y_lagrange, label='Nodes', color='purple', s=25, marker='o')

            axs[i, 1].scatter(self.x_col, self.y_col, label='Original', color='red', s=5)
            axs[i, 1].plot(interpolate_x_cubic_splines, interpolate_y_cubic_splines, label='Interpolation', color='green')
            axs[i, 1].scatter(org_x_cubic_splines, org_y_cubic_splines, label='Nodes', color='purple', s=25, marker='o')

            # Legend
            axs[i, 0].legend()
            axs[i, 0].set_title('Lagrange')
            axs[i, 0].set_xlabel('Distance')
            axs[i, 0].set_ylabel('Elevation')

            axs[i, 1].legend()
            axs[i, 1].set_title('Cubic Spline')
            axs[i, 1].set_xlabel('Distance')
            axs[i, 1].set_ylabel('Elevation')
            i += 1

        plt.show()

    def __call_interpolation_method(self, no_of_points: int, func) -> (List[Any], List[Any], List[Any], List[Any]):
        no_of_org_points: int = len(self.x_col)

        subset_index_list = [int(i) for i in InterpolationUtils.create_list_of_numbers(0, no_of_org_points - 1, no_of_points)]
        subset_org_x = [self.x_col[i] for i in subset_index_list]
        subset_org_y = [self.y_col[i] for i in subset_index_list]

        interpolate_x = InterpolationUtils.create_list_of_numbers(min(self.x_col), max(self.x_col), 1000)
        interpolate_y = func(subset_org_x, subset_org_y, interpolate_x)

        return interpolate_x, interpolate_y, subset_org_x, subset_org_y

def main():
    no_of_points_list: List[int] = [
        5, 15, 30, 50
    ]

    files: List[str] = [
        "data/MountEverest.csv",
        "data/Unsyncable_ride.csv",
        "data/stale.txt"
    ]

    for file in files:
        interpolation = Interpolation(file)
        interpolation.show_plot(no_of_points_list)


if __name__ == "__main__":
    main()
