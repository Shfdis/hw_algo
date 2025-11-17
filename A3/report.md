# Отчет A3: Анализ INTROSORT

## Методы

- Стандартный QUICK SORT со случайным выбором опорного элемента
- INTROSORT: QUICK SORT с переключением на HEAP SORT при глубине 2*log2(N) и INSERTION SORT при размере <= 16

## Параметры

- Размеры: 1000-50000, шаг 2000
- Типы: случайные, обратно отсортированные, почти отсортированные
- Замеров: 5

## Выводы

1. INTROSORT избегает худшего случая O(N^2) стандартного QUICK SORT
2. INTROSORT стабильнее на обратно отсортированных данных
3. При больших размерах INTROSORT может быть медленнее из-за переключения на HEAP SORT
4. Переключение на INSERTION SORT улучшает производительность на малых подмассивах

## Файлы

- `results/comparison.png`
- `results/comparison_all.png`
- `results/standard_*.txt`
- `results/hybrid_*.txt`

## Ссылка на репозиторий: https://github.com/Shfdis/hw_algo
## Id посылки: 349134616

