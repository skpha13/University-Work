package sealed.bird;

public sealed interface Bird permits Penguin, Sparrow, RecordBird {
}
