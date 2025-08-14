
# programa 1
"""
nome = input("Digite seu nome: ")
idade =input("Digite sua idade: ")

print("Olá, " + nome + "! Você tem " + idade + "anos.") 

"""
# programa 2

"""
peso = float(input("Qual o seu peso? "))
altura = float(input("Qual sua altura? "))

imc = peso/(altura * altura)

print(imc)

"""

# programa 3
"""
idade = int(input("Qual a sua idade? "))

if idade <= 12:
    print("Criança")
elif idade >= 13 and idade <= 17:
    print("Adolescente")
elif idade >= 18 and idade <= 59:
    print("Adulto")
else:
    print("Idoso")   

"""
# programa 4 

"""
maiores_de_idade = 0 

for i in range(5):
    idade = int(input(f"Digite a {i+1} idade: "))

    if idade >= 18:
        maiores_de_idade += 1


print(f"Existem {maiores_de_idade} pessoas maiores de idade.")

"""

# programa 5

"""
maior_numero = None

for i in range(10):
    numero = int(input(f"Digite o {i+1} numero: "))

    if maior_numero is None or numero > maior_numero:
        maior_numero = numero

print(f"O maior numero é: {maior_numero}.")

"""
# programa 6

"""
# Inicializa a variável de soma
soma = 0

# Laço while para continuar pedindo números até o usuário digitar 0
while True:
    numero = int(input("Digite um número (0 para parar): "))
    
    if numero == 0:
        break  # Sai do loop se o número for 0
    
    soma += numero  # Soma o número digitado à variável soma

print("A soma dos números digitados é:", soma)

"""

# Programa 7
"""
def fatorial(n):
    if n == 0 or n == 1:
        return 1
    else:
        return n * fatorial(n - 1)

# Exemplo de uso
numero = int(input("Digite um número para calcular o fatorial: "))
resultado = fatorial(numero)
print(f"O fatorial de {numero} é {resultado}")

"""
