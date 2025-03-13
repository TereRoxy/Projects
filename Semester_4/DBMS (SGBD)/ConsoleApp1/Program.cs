// See https://aka.ms/new-console-template for more information
Console.WriteLine("Hello, World!");
int suma = 0;
for (int i = 1; i <= 1001; i++)
{
    if (i % 2 == 1)
    {
        suma = suma + i * i + i * i - (i - 1);
    }
    else
    {
        suma = suma + i * i + 1 + i * i + 1 - i;
    }
}
suma = suma - 1;
//print result
Console.WriteLine("Suma: " + suma);