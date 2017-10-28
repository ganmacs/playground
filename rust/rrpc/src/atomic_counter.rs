use std::sync::Arc;
use std::sync::atomic::Ordering;
use std::sync::atomic::AtomicUsize;

#[derive(Debug, Clone)]
pub struct Counter {
    value: Arc<AtomicUsize>,
}

impl Counter {
    pub fn new(value: usize) -> Self {
        Counter { value: Arc::new(AtomicUsize::new(value)) }
    }

    pub fn up(self) -> u64 {
        self.value.fetch_add(1, Ordering::SeqCst) as u64
    }
}
